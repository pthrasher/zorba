import module namespace ddl = "http://www.zorba-xquery.com/modules/store/static/collections/ddl";
import module namespace dml = "http://www.zorba-xquery.com/modules/store/static/collections/dml";
import module namespace iddl = "http://www.zorba-xquery.com/modules/store/static/indexes/ddl";
import module namespace idml = "http://www.zorba-xquery.com/modules/store/static/indexes/dml";

import module namespace data = "http://www.test.com/" at "paging.xqlib";

data:init();
(
  <one>{
    idml:probe-index-point-value-skip($data:idx-age-point-val, 1, 3)
  }</one>, 
  <two>{
    count(idml:probe-index-point-value-skip($data:idx-age-point-val, 1, 3))
  }</two>, 
  <three>{
    idml:probe-index-range-value-skip($data:idx-age-range-val,  
                                      2, 3, 4, true(), true(), true(), true())
  }</three>, 
  <four>{
    count(idml:probe-index-range-value-skip($data:idx-age-range-val,
                                            2, 3, 4, 
                                            true(), true(), true(), true()))
  }</four>
)

