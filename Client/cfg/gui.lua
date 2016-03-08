function someFunc(n) 
  if n < 2 then
	return 1 
	end 
  return fib(n - 2) + fib(n - 1) 
end

AddMenuItem("File/Open","OpenFileScript") ;
AddMenuItem("File/Close","OpenFileScript") ;
AddMenuItem("File/Save","OpenFileScript") ;
AddMenuItem("File/Save as","") ;
AddMenuItem("File/Recent","sdfsdf") ;

AddMenuItem("Edit/Undo","cfg/UndoScript.lua") ;
AddMenuItem("Edit/Redo","cfg/RedoScript.lua") ;


AddMenuItem("Edit/Advance/check all/weoif","cfg/complex.lua") ;