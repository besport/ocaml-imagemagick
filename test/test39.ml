
let () =
  Magick.initialize ();
  let img = Magick.get_canvas ~color:"#63ED52" ~width:380 ~height:220 in

  let ctx = Magick.Draw.allocate_context img in

  Magick.Draw.stroke_color_string ctx "black";
  Magick.Draw.fill_color_string ctx "#B54082";
  Magick.Draw.stroke_width ctx 3.0;
  Magick.Draw.round_rectangle ctx ~p1:(100.0, 20.0) ~p2:(260.0, 100.0) ~r:(16.0, 16.0);
  Magick.Draw.bezier ctx ~coords:[|
    (20.0, 20.0);
    (80.0, 20.0);
    (80.0, 80.0);
    (20.0, 140.0);
  |];
  Magick.Draw.line ctx ~x1:20.0 ~y1:20.0 ~x2:20.0 ~y2:140.0;
  Magick.Draw.render ctx;

  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

