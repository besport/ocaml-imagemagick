open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.charcoal img ~radius:3.0 ~sigma:6.0 in
  let img3 = Magick.implode img ~amount:2.0 in
  let img4 = Magick.oil_paint img ~radius:6.0 in
  let img5 = Magick.swirl img ~degrees:80.0 in
  let img6 = Magick.wave img ~amplitude:3.0 ~length:4.0 in
  Magick.display img2;
  Magick.display img3;
  Magick.display img4;
  Magick.display img5;
  Magick.display img6;
  Magick.destroy ();
;;

