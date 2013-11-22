import module namespace jsd = "http://jsound.io/modules/jsound"; 

let $jsd :=
  {
    "$namespace" : "http://www.example.com/my-schema",
    "$types" : [
      {
        "$name" : "foo",
        "$kind" : "object",
        "$content" : {
          "foo" : {
         (: "$type" missing :)
            "$optional" : true
          }
        }
      }
    ]
  }

let $instance := "foo"

return jsd:jsd-validate( $jsd, "foo", $instance )

(: vim:set syntax=xquery et sw=2 ts=2: :)
