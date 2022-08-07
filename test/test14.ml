
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.sample img ~width:120 ~height:120 in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

