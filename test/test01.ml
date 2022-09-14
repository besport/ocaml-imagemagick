
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.write_image img ~filename:"_out.jpg";
  Magick.destroy ();
;;

