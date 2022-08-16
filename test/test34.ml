
let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let ctx = Magick.Draw.allocate_context img in

  Magick.Draw.stroke_color_string ctx "black";
  Magick.Draw.fill_color_string ctx "#FF00FF";
  Magick.Draw.stroke_width ctx 3.0;
  Magick.Draw.rectangle ctx ~x1:20.0 ~y1:20.0 ~x2:200.0 ~y2:80.0;
  Magick.Draw.circle ctx ~ox:100.0 ~oy:60.0 ~px:100.0 ~py:100.0;
  Magick.Draw.arc ctx ~p1:(80.0, 40.0) ~p2:(260.0, 100.0) ~rot:(30.0, 240.0);
  Magick.Draw.render ctx;

  Magick.display img;
  Magick.destroy_image img;
  Magick.destroy ();
;;

