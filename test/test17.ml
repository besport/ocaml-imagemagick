
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.shade img ~gray:2 ~azimuth:60.0 ~elevation:12.0 in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

