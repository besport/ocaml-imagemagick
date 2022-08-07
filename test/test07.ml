
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.destroy_image img;
  Magick.destroy ();
;;

