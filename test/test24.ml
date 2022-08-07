open Magick

let () =
  Magick.initialize ();
  let img1 = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.crop img1 { x = 80; y = 30; width = 160; height = 60 } in
  Magick.display img2;
  Magick.destroy_image img1;
  Magick.destroy_image img2;
  Magick.destroy ();
;;

