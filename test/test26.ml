open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.contrast img ~sharpen:40;
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

