
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.sharpen img ~radius:4.0 ~sigma:2.8 in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

