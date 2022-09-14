
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.resize img ~width:140 ~height:140 ~filter:Magick.Filter.Lanczos ~blur:1.0 () in
  Magick.destroy_image img;
  Magick.display img2;
  Magick.destroy ();
;;

