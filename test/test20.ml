
let () =
  Magick.initialize ();
  let img1 = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.minify img1 in
  let img3 = Magick.magnify img1 in
  Magick.destroy_image img1;
  Magick.display img2;
  Magick.display img3;
  Magick.destroy_image img2;
  Magick.destroy_image img3;
  Magick.destroy ();
;;

