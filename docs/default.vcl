#-e This is a basic VCL configuration file for varnish.  See the vcl(7)
#man page for details on VCL syntax and semantics.
#

# The VCL syntax changed between Varnish versions.
# TODO: Document the VCL differences.

# load the ESI-blocks VCL
# This should be in the same folder, or given an absolute path to the VCL.
include "esi_blocks.vcl";


backend default {
  .host = "127.0.0.1";
  .port = "8080";
}



sub vcl_recv {
  call esi_block__recv;
}

sub vcl_hash {
  call esi_block__hash;
}

sub vcl_fetch {
  # don't ESI anything with a 3/4 letter extension
  # (e.g. don't try to ESI images, css, etc).
  if (! req.url ~ "\..{3,4}$") {
    esi;
  }

  call esi_block__fetch;
}




