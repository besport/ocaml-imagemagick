open Magick

let () =
  Magick.initialize ();
  let img1 = Magick.read_image ~filename:"image.png" in
  let width, height = (40, 20) in
  let img2 = Magick.shave img1 (width, height) in
  Magick.display img2;
  Magick.destroy_image img1;
  Magick.destroy_image img2;
  Magick.destroy ();
;;

