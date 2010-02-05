// $Id: README.txt$

The rough plan so far......

Goal:
Create a Edge Side Includes module that will support reverse proxies with this functionality. It will be built in a abstracted and
pluggable fashion so both the reverse proxies and the Drupal caching layer is exchangeable  

Initial Implementation:
Our initial effort is going be look at Varnish as seems to be well adopted in Drupal, but will design with the idea pluggable extensions 
being added when needed.

Considerations:
 1. If you only have one ESI call on a page this is very straight forward
 2. We don't have a option 1 situation.
 3. If you have multiple calls you could just do one call and use JavaScript to do DOM manipulation (again we can't due to accessibility 
     on the site) the jquery (or equiv) can be passed back with the ESI data
 
Process flows;

Requests: 
    -> [path]esi.php[with arguments] 
    -> controller picks up request loads appropriate config 
       -> The config is chosen using settings admin UI but on save we write that information to both the db and to a settings/config file in a know
            location on disk, the esi.php is then able to read that and have all the information necessary to draw from the chosen cache store
            without having to bootstrap
    -> a cache lookup is performed based url hash (plus salt or token or something/something)
    -> If hit return the data
    -> Fail invoke Frupal bootstrap and generate the data
    
 Page building:
   -> At the highest point in any given template create a controller ESI call this will include all of the other subsequent 
        ESI calls on the page. This is where we will front load all the caching
   -> All other ESI calls will only call the data needed
   -> Initially we will use a get with args call e.g. [path to esi]/esi.php?q=node/[nid](or user etc)&
          args=/module_function:salt:variables/module_function:salt:variables/etc
      -> The salt could be a user_id, a node_id, other caching needs
      -> variables are extra data need in full bootstrap etc
   -> We should look at using blocks where possible for our ESI as placement it easy and UI configuration can be added