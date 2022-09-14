
let () =
  Magick.initialize ();
  let img1 = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.flip img1 in
  let img3 = Magick.flop img1 in
  Magick.display img2;
  Magick.display img3;
  Magick.destroy_image img1;
  Magick.destroy_image img2;
  Magick.destroy_image img3;
  Magick.destroy ();
;;

