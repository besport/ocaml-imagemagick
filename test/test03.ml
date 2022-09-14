
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.write_image img ~filename:"/tmp/dont_exist/out.jpg";  (* test failure *)
  Magick.destroy ();
;;

