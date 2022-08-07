
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"dont_exist.png" in  (* test failure *)
  Magick.destroy_image img;
  Magick.destroy ();
;;

