
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.display img;
  Magick.destroy ();
;;

