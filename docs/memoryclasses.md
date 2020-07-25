```
module Car

import Std.Date



WheelSet


type Car is
class


self : Car.type.pointer
#meta(self) = fn() -> _:MetaPrivate
#end


engine: Engine
#meta(engine) = fn() -> _:MetaProtected 
_.default = engine.type.default()
#end

body: Body
#meta(body) -> _:MetaPublic
#end



transmission: Optional{Transmission}
#meta(transmission) -> _:MetaSetPrivate
  _.default = Nothing
#end


wheels: WheelSet{2,2}
#meta(wheels) -> _:MetaPublic

  _.set = fn ( wheelset_to_set : wheels.type ) -> :wheels.type
    let cout = std.output.stream.cout
    if ( wheelset_to_set !=  )
       cout(`somebody set wheels`)
    end
  end

#end


model: Optional{Model}
#meta(model) -> _:MetaProtected
#end


manufatoring_date: Std.Date
#meta(manufatoring_date) -> _:Meta
  _.get = #public
  _.set = #const
#end


id: Id
#meta(id) -> _:MetaFullProtected
#end


fn init(@id:id.type,@date:manufactoring_date.type,@model:model.type,  )

end


end //type Car


```