
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.edge img ~radius:4.0 in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

