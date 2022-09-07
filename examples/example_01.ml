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
  let t_img = Magick.read_image ~filename in
  let u_img = Magick.clone t_img in

  print_endline " Here is the original image";
  Magick.display t_img;

  let u_img = Magick.blur u_img  ~sigma:2.4 () in
  Magick.modulate u_img "70,100,100";
  Magick.negate u_img 0;

  print_endline " Intermediate processing";
  Magick.display u_img;

  let t_img = Magick.blur t_img ~sigma:0.3 () in  (* smooth the path a little *)
  let u_img = Magick.roll u_img ~x_offset:2 ~y_offset:1 in
  Magick.composite t_img u_img ~compose:CompositeOp.Lighten ();

  print_endline " Here is the result\n";
  Magick.display t_img;

  Magick.destroy_image t_img;
  Magick.destroy_image u_img;
  Magick.destroy ();
;;

(* vim: sw=2 ts=2 sts=2 et
 *)
