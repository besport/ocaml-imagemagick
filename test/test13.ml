
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.motion_blur img ~radius:0.0 ~sigma:12.0 ~angle:16.0 in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

