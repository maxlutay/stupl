

any function  accept 1 tuple, return 1 tuple, tuple is key-value hashmap

fn <function name> ( @<arg1 name>, @<arg2 name> : <arg1 and arg2 type>, @<arg3 name> : <arg3 type> ) -> <return variable name> : <return type> 
<body>
end 

fn <function name> ( @<arg1 name> : <arg1 type>, @<rest args tuple name>... : <rest arg type> )
-> <return variable name> : <return type> ::final ::override

    var:auto = @<rest args tuple name>.at() #question about indexes 0, 1 or specifier

end 



fn getnothing(@something: Some_Type) -> : <Nothing
    return Nothing()
end

type Branch_Select is
union
    TypeX | TypeY | TypeZ| TypeQ | Int 
end

fn getmultiple( @branch_selector: Branch_Select ) -> : Tuple{size= 5, type=ReturnElements} 
    case(@branch_selector)(Tuple{size=auto,type=Function(@branch_selector.type)->Nothing }(
        fn() -> 

    )
end





type Type_AuB is
union
    TypeA | TypeB
end


fn getitems( Arguments( @arg1 :TypeX, @arg2 :TypeY, @arg3 : Type_AuB, @arg4:...{TypeZ} , @arg5: TypeA, @arg6:...{TypeB,length=4}, @arg7:...{type=TypeB,length -lt 5, length -gt 2} )      )
#... is generic type, mean some type of array 








