open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.modulate img "90,150,100";
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

