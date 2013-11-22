import module namespace jsd = "http://jsound.io/modules/jsound"; 

let $jsd :=
  {
    "$namespace" : "http://www.example.com/my-schema",
    "$types" : [
      {
        "$kind" : "atomic",
        "$name" : "foo",
        "$baseType" : "string",
        "$constraints" : [ true ] (: must be array of string :)
      }
    ]
  }

let $instance := "foo"

return jsd:jsd-validate( $jsd, "a-string-enum", $instance )

(: vim:set syntax=xquery et sw=2 ts=2: :)
