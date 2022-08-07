open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.negate img 3;
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

