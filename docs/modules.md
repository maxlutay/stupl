

Modules

Should:
 * first name letter be capital letter
 * declared as 
```
module <name>

end
```

Can contain:
    * modules
    * types
    * functions
    * const entities
    * mutable entities



Syntax:

Basic:

```
module MyModuleName

end
``` 
- ok





```
//file SomeModuleName.stupl


module SomeModuleName

type Foo

end ;Foo


type Bar

end ;Bar


end ;SomeModuleName



module MyModuleName


type MyTypeName is
class
end ;MyTypeName

fn MyFnName(@myarg1:Foo ) -> :SomeModuleName.
end ;MyFnName


end ;MyModuleName


```





