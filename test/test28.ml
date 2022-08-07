open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.gamma img ~level:"1.0,2.2,0.45";
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

