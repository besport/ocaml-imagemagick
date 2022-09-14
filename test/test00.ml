
let () =
  Magick.initialize ();
  let img = Magick.get_canvas ~color:"#ED6352" ~width:380 ~height:220 in
  Magick.display img;
  Magick.destroy ();
;;

