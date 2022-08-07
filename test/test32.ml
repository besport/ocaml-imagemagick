open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.normalize img;
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

