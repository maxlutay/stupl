

    type Person is
    mutable class 

    this : Person.type.ref = Person()

    #name: String
    #position: Position
    #sex: _Optional{Sex}

    address: Address
    birth_date : _Optional{Date} 
    ignore_list: Std.Array{ Person.type.ref } 
    friends_list: Std.Array{ Person.type.ref }
    mate_list: Std.Array { Person.type.ref }


    type _Optional{T} is 
    union ( <T | T | Nothing )
    end

    fn Person( .#name, .#position, .address, .birth_date = Nothing, #sex ) -> : Person.type.ref
    end


    fn _decide(@...choice: Choice) -> Choice
      const i:Int = Std.random{Int}()
      return ...choice[i];
    end


    fn meet( @group: Std.Array{Person.type.ref} ) -> Nothing
      let i : uint64

      for somebody: @group.elements.type.ref in range(@group) 
        i = i + 1
        if( (i-1) >= @group.elements.last.i)
          for.skip()
        
        else
        if( like(somebody) )
            //
        end

      end //for

      end

    fn date(@somebody : Person ) -> Nothing
    end

    fn ignore(@somebody: Person ) -> Nothing

    end


    end //Person














