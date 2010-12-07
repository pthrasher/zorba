import module namespace zorba-csv = "http://www.zorba-xquery.com/modules/csv";


let $options := 
<options>
  <first-row-is-header/>
  <csv separator=","
       quote-char="&quot;"
       quote-escape="&quot;&quot;"/>
</options>
return
zorba-csv:parse(
zorba-csv:serialize(
(<row1>
  <f1>value1</f1>
  <f2>"value2"</f2>
  <f3>value3,value33</f3>
  <f4>value4</f4>
</row1>,
<row2>
  <f1>value11</f1>
  <f2>value12</f2>
  <f3>value13</f3>
  <f4>value14</f4>
</row2>,
<row3>
  <f11>value21</f11>
  <f22>value22</f22>
  <f33>value23</f33>
  <f44>value24</f44>
</row3>),
$options),
$options)