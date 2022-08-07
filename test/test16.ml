open Magick

let composite_operators = [|
  CompositeOp.Undefined;
  CompositeOp.Over;
  CompositeOp.In;
  CompositeOp.Out;
  CompositeOp.Atop;
  CompositeOp.Xor;
  CompositeOp.Plus;
  CompositeOp.Minus;
  CompositeOp.Add;
  CompositeOp.Subtract;
  CompositeOp.Difference;
  CompositeOp.Multiply;
  CompositeOp.Bumpmap;
  CompositeOp.Copy;
  CompositeOp.CopyRed;
  CompositeOp.CopyGreen;
  CompositeOp.CopyBlue;
  CompositeOp.CopyOpacity;
  CompositeOp.Clear;
  CompositeOp.Dissolve;
  CompositeOp.Displace;
  CompositeOp.Modulate;
  CompositeOp.Threshold;
  CompositeOp.No;
  CompositeOp.Darken;
  CompositeOp.Lighten;
  CompositeOp.Hue;
  CompositeOp.Saturate;
  CompositeOp.Colorize;
  CompositeOp.Luminize;
  CompositeOp.Screen;
  CompositeOp.Overlay;
  CompositeOp.CopyCyan;
  CompositeOp.CopyMagenta;
  CompositeOp.CopyYellow;
  CompositeOp.CopyBlack;
  CompositeOp.Divide;
  CompositeOp.HardLight;
  CompositeOp.Exclusion;
  CompositeOp.ColorDodge;
  CompositeOp.ColorBurn;
  CompositeOp.SoftLight;
  CompositeOp.LinearBurn;
  CompositeOp.LinearDodge;
  CompositeOp.LinearLight;
  CompositeOp.VividLight;
  CompositeOp.PinLight;
  CompositeOp.HardMix
|]

let compose =
  Random.self_init ();
  let n = Array.length composite_operators in
  composite_operators.(Random.int n)

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.blur img ~radius:0.0 ~sigma:6.0 () in
  Printf.printf "composite_operator: %s\n%!"
    (Magick.string_of_composite_operator compose);
  Magick.composite img ~compose img2 ~x_offset:0 ~y_offset:0 ();
  Magick.display img;
  Magick.destroy ();
;;

