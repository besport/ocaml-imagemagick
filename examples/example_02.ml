#!/usr/bin/env ocaml
#load "magick.cma"
open Magick

let () =
  let argc = Array.length Sys.argv in
  if (argc < 2) then begin
    prerr_endline ("Usage:\n" ^ Sys.argv.(0) ^ " <black & white image file>");
    exit 1
  end

let () =
  Magick.initialize ();
  let filename = Sys.argv.(1) in
  let t_img = read_image ~filename in
  let u_img = clone t_img in

  print_endline " Here is the original image";
  display t_img;

  let u_img = blur  u_img  ~sigma:2.8 () in
  negate  u_img 1;
  modulate  u_img "80,100,100";
  negate  u_img 1;
  print_endline " Intermediate processing";
  display  u_img;

  let t_img = blur  t_img  ~sigma:0.4 () in
  negate  t_img 1;
  let u_img = roll  u_img ~x_offset:(-3) ~y_offset:2 in
  composite  t_img u_img ~compose:CompositeOp.Lighten ();

  print_endline " Here is the result\n";
  display  t_img;
;;

