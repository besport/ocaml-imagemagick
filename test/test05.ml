
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let w = Magick.image_width img in
  let h = Magick.image_height img in
  Printf.printf "image size: %d x %d\n%!" w h;
  assert ( (w, h) = (350, 110) );
  Magick.destroy ();
;;

