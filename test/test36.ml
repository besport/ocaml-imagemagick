open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.charcoal img ~radius:3.0 ~sigma:6.0 in
  Magick.display img2;
  Magick.destroy ();
;;

