###
# Custom subroutines to provide ESI support for Drupal blocks with the
# Drupal ESI module.
##

/**
 * Alter the hash per-user or per-role
 */
sub esi_block__hash {
  # Customise the hash if required.
  if ( req.http.X_BLOCK_CACHE ) {
    if( req.http.X_BLOCK_CACHE == "USER" ) {
      if( req.http.Cookie ~ "SESS" ) {
        # This pulls the session-name and session-id from the cookie string.
        set req.http.X-SESSION-ID =
          regsub( req.http.Cookie, "^.*?SESS(.{32})=([^;]*);*.*$", "\1\2" );

        # add the session info to the hash.
        set req.hash += req.http.X-SESSION-ID;
      }
    }

    if( req.http.X_BLOCK_CACHE == "ROLE" ) {
      # Roles are identified by a cookie beginning RSESS
      if( req.http.Cookie ~ "RSESS" ) {
        # This pulls the role info from the cookie string.
        set req.http.X-ROLE-SESSION-ID =
          regsub( req.http.Cookie, "^.*?RSESS(.{32})=([^;]*);*.*$", "\1\2" );

        # add the session info to the hash.
        set req.hash += req.http.X-ROLE-SESSION-ID;
      }
    }
  }
}


/**
 * Add an http header if an ESI block has per-user or per-role cache rules
 */
sub esi_block__recv {

  # The URL structure of ESI blocks identifies which are per-user or per-role.
  # e.g. /esi/block/garland:left:foo:bar/node%2F1/CACHE=USER
  # Add a header to show if we're using a particular cache strategy.
  if( req.url ~ "^/esi/block" ) {

    # look for a cache instruction. This should be the final argument to the URL
    # and should have the value 'USER' or 'ROLE'.
    if ( req.url ~ "^.*/CACHE=[^/]*$" ) {

      # Set an HTTP_X_BLOCK_CACHE header to be appropriate setting.
      set req.http.X_BLOCK_CACHE =
        regsub( req.url, "^.*/CACHE=([^/]*)$", "\1" );

      # Strip the cache-instruction from the end of the URL.
      set req.url =
        regsub( req.url, "^(.*)/CACHE=[^/]*$", "\1" );
    }
  }

  # Ignore presence of cookies, etc, for ESI requests:
  # Always try to lookup ESIs from the cache.
  if(req.url ~ "^/esi.*") {
    lookup;
  }
}


/**
 * Cache ESI'd block content.
 */
sub esi_block__fetch {
  # ESI blocks with per-user or per-role config have a cache-control: private
  # header.  This removes the header and inserts the block into the cache.
  if( obj.http.Cache-Control ~ "private" ) {
    unset obj.http.Set-Cookie;
    unset obj.http.Cache-Control;
    deliver;
  }
}
