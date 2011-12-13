#!/usr/bin/env ocaml
#load "magick.cma"
open Magick
open Imper

let () =
  let img = get_canvas ~width:400 ~height:300 ~color:"#C8E0FF" in

(* The clouds *)
  List.iter (fun (cx, cy) ->
    draw_ellipse img ~cx ~cy
        ~rx:50 ~ry:20 ~fill_color:(color_of_string "#FFFB") ()
  ) [ (20, 40); (60, 55); (90, 30); (120, 65); (175, 35); ];

(* The hills *)
  let path = "M -10 300 L -10 230 C 160 258 188 190 275 188 C 320 188 382 200 410 220 L 410 300" in
  draw_path img ~path
      ~fill_color:(color_of_string "#7C80")
      ~stroke_color:(color_of_string "#4A70")
      ~stroke_width:4.0 ();

(* The building, and its door *)
  List.iter (fun (coords, fill, stroke) ->
    draw_polyline img ~coords
        ~fill_color:(color_of_string fill)
        ~stroke_color:(color_of_string stroke)
        ~stroke_width:7.0
        ~line_cap:ButtCap
        ~line_join:MiterJoin ()
  ) [ ([| (240, 230); (265,  60); (305,  60); (330, 230) |], "#DCB", "#764");
      ([| (265, 230); (270, 195); (300, 195); (305, 230) |], "#CBA", "transparent") ];

(* Open Source logo *)
  List.iter (fun (color, stroke_width) ->
    draw_ellipse img
        ~stroke_width
        ~stroke_color:(color_of_string color)
        ~fill_color:(color_of_string "transparent")
        ~cx:285 ~cy:214
        ~rx:9 ~ry:9
        ~a0:115 ~a1:425 ()
  ) [("black", 8.2); ("green", 6.2)];

(* The arms *)
  List.iter (fun coords ->
    draw_bezier img ~coords
        ~fill_color:(color_of_string "#FFF8F255")
        ~stroke_color:(color_of_string "#6548")
        ~stroke_width:4.0
        ~line_cap:RoundCap ()
  ) [ [| (180,  90); (250, 20); (320, 140); (390,  70) |];
      [| (275, -25); (345, 45); (225, 115); (295, 185) |] ];

(* Title *)
  draw_text img ~text:"Objective Caml\nImageMagick" ~font:""
      ~x:15 ~y:168
      ~point_size:20.0
      ~stroke_width:1.0
      ~fill_color:(color_of_string "#0132")
      ~stroke_color:(color_of_string "#48A6") ();

(* Surrounding *)
  draw_round_rectangle img
      ~x0:(-4) ~y0:(-4)
      ~x1:404 ~y1:304
      ~wc:28 ~hc:28
      ~fill_color:(color_of_string "transparent")
      ~stroke_color:(color_of_string "black")
      ~stroke_width:16.0 ();

  display img;

(* vim: sw=2 sts=2 ts=2 et fdm=marker
 *)
