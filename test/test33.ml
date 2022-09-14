open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  Magick.level_channel img
      ~channel:Channel.Blue
      ~black_point:1.0
      ~mid_point:1.0
      ~white_point:1.0;
  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

