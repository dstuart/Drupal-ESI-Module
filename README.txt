REQUIREMENTS

Use of the ESI module requires a reverse proxy with ESI support.
Varnish would be a good choice.


USING THE ESI MODULE

The ESI module will replace blocks with ESI include tags - which look like:
<esi:include src="/esi/block/....." />
The reverse-proxy will remove the ESI tags from the page, and replace each one
with the appropriate block content.  The proxy should be configured to cache
the block content appropriately for the block-cache configuration, so that
blocks which change per-user or per-role have separate caches for each context.
The example VCL demonstrates how this is done with Varnish.


ROLE-BASE COOKIES

To support cacheing of role-based blocks, the proxy needs a way of recognising
which roles a user has.  On login, a cookie is set by the ESI module with a
unique hash for each combination of roles; for example, all users who have no
role will have hash a; users who are in role foo (and only role foo) will have
hash b; users who are in role foo and role bar will have hash c; etc.
The proxy has no way of interpreting which roles a user has, but can
distinguish each unique combination of roles.


CONFIGURATION

The module stores 3 variables:
 - esi_seed_key_rotation_interval
   How often the seed key should change (in seconds). Defaults to daily.

 - esi_seed_key_last_changed
   When the seed key was last changed (unix timestamp)

 - esi_seed_key
   The current 'seed' (a 32-character string)

The esi_seed_key_rotation_interval variable may be configured in settings.php.
In most cases, it's best to allow the module to manage the other 2 fields
automatically.


VARNISH VCLs

Two VCLs are provided:
- docs/esi_blocks.vcl
  This VCL provided custom sub-routines to handle ESI-block integration.
  This is designed to be included from another VCL.
  NB: There is also a doc/esi_blocks-2_0.vcl for people that are using varnish < 2.1

- docs/default.vcl
  This is an example default.vcl, showing how the ESI-blocks VCL can be
  included.
