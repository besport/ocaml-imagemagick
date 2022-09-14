
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.svg" in
  Magick.write_image img ~filename:"_out.png";
  Magick.destroy ();
;;

