
let () =
  for i = 1 to pred (Array.length Sys.argv) do
    if Sys.argv.(i) = "-pthread" then ()
    else begin
      let arg = Sys.argv.(i) in
      match arg.[0], arg.[1] with
      | '-', 'l' -> Printf.printf " -cclib %s" arg
      | '-', 'L' -> Printf.printf " -ccopt %s" arg
      | _ -> ()
    end
  done
