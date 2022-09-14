open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.level img ~level:"10,1.0,65000";
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

