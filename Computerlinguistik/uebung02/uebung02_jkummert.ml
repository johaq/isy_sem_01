let rec thue s = match s with
[] -> s
|a::l ->	if(a='0') then ('0'::'1'::thue l)
	 	else ('1'::'0'::thue l);;

let rec morse s n = 	if(n=0) then s
			else morse (thue s) (n-1);;

let plaetten list = List.concat list;;
