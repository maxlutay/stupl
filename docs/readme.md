
 ## this folder needs rework !!! 
 #### only draft presented


## current design topics and questions(not in order):

- **Q**:do functions arguments need specific notation? why? which ? is '@' ok for this? or '#' ? or '\_'?

**A**: _Either no notation or '@' seems the best choice_ 
 
- **Q**:do functions need 'return' statement? for which purposes?

**A**: _I propose to eliminate return statements. By either returning last line or assigning return variable;_


- **Q**: do functions need named return variable, optional or mandatory ?

**A**: _IMO functions need return variable (which will completely eliminate return statement). Optional will make some default return type for all functions. Mandatory will be a source of inconvinience for programmers._


- **Q**: do functions need "spread/rest operator" argument expansion? Syntax of specifing types for such operator? do such operator need possibility of specifing count of arguments? what about templating such operator? what language mechanism would be used?

**A**: _Probably yes, such operator is useful in Ecmascript. Not sure, but it should follow template style. Yes, if multiple argument expansion would be implemented. with templates. Probably templates, not macro. _


- **Q**: do functions need multiple argument expansion option? how to distinguish between multiple expansion operators?

**A**: _Multiple argument expansion option could potentially enrich language. But i am still not sure if we need more or less complexity. Maybe we even do not need function argument expansion at all._


- **Q**: how to make pointer/reference/value copy/move passing more convenient?

- **Q**: syntax for class memory management? how to specify allocation functions? are stack memory needed at all? syntax for class construction on heap and stack ?

- **Q**: syntax for type information of variable? dot notation inherited from common parent object? 

- **Q**: syntax for private/public class memebers? maybe use templates annotations? what about groups of variables? grouping templates? public interfaces? i do not like to add special syntax like in c++, c#, java etc.

- **Q**: syntax for templates? `%//%`? `#[]`? `#[]#`? `@{}`? `%{}` ? 

- **Q**: syntax for multithreading and atomics? templates again? multithreaded memory management syntax?

- **Q**: syntax for 1 line comment? only `;`? what about `//` and `#`? 

**A**: _`;comment` seems to be the best choice for 1line comment, all after `;` ignored till line end_


- **Q**: do we need multiline comment? syntax for multiline comment using `;`? or use '/\*\*/'? what about nested comments?

**A**:  _I do not like something about `/**/`. Even if nesting would be supported. Probably only 1 line comments `;` will be supported. 


- **Q**: do special syntax for interfaces needed? 

**A**: _Probably not_


- **Q**: do declaration of inheritance need `public/protected/private` specifiers?


**A**: _I think more yes than no_



- **Q**: what about multiple inheritance? if it will be supported, what is the way for managing memory consistency ? specifying base class ? what is syntax for it ?

- **Q**:do templates need inheritance hierarchy? like `<| classname` for 'type that inherits from classname'? 

- **Q**: would module system implement export? what export synatax ?

- **Q**: do functions should be separate first-order 'entity' or be class with apply method overloaded ? should functions inherit from some 'god parent type' ? should classes, enums, unions etc. inherit from 'god parent type' too ?  

- **Q**:?todo







