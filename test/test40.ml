open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in

  Magick.set_image_attribute img ~key:"author" ~value:"Jane Smith";
  Magick.set_image_attribute img ~key:"commiter" ~value:"John Doe";
  Magick.set_image_attribute img ~key:"uploader" ~value:"Mister T";

  let key = "commiter" in
  let value = Magick.get_image_attribute img ~key in
  Printf.printf " (%s, %s)\n" key value;

  Magick.destroy_image img;
  Magick.destroy ();
;;

