let nth l i = (int_of_string (List.nth l i));;
let n = read_int() in
let l2 = read_line() in
let tokens = Str.split (Str.regexp " ") l2 in
let rec process k t =
  if k < 0 then 0
  else (
    let a = (nth tokens k) in
    ((if a < 0 then 1 else 0) + (process (k-1) t))
  ) in
let res = process (n - 1) tokens in
print_int(res);;
print_string("\n")
