import schema namespace 
  s = "simple.xsd" 
  at "simple.xsd";

validate 
{
    <product xmlns='simple.xsd'>
    	<name>p1</name>
    	<number>1</number>
    	<extraElement> text </extraElement>
    </product>
}
