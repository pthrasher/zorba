import module namespace jsd = "http://jsound.io/modules/jsound"; 

let $jsd :=
  {
    "$namespace" : "http://www.example.com/my-schema",
    "$types" : [
      {
        "$kind" : "atomic",
        "$name" : "a-string-enum",
        "$baseType" : "string",
        "$enumeration" : [ "foo", 42 ] (: must be array of string :)
      }
    ]
  }

let $instance := "baz"

return jsd:jsd-validate( $jsd, "a-string-enum", $instance )

(: vim:set syntax=xquery et sw=2 ts=2: :)
