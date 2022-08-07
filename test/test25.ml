open Magick

let () =
  Magick.initialize ();
  let img1 = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.shave img1 { x = 0; y = 0; width = 40; height = 20 } in
  Magick.display img2;
  Magick.destroy_image img1;
  Magick.destroy_image img2;
  Magick.destroy ();
;;

