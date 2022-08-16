open Magick

let () =
  Magick.initialize ();
  let img = Magick.read_image ~filename:"image.png" in
  let img2 = Magick.charcoal img ~radius:2.0 ~sigma:5.0 in
  let imglst = Magick.ImgList.new_image_list () in
  let imglst2 = Magick.ImgList.append_image imglst img in
  let imglst3 = Magick.ImgList.append_image imglst2 img2 in
  let imglst4 = Magick.morph imglst3 ~frames:6 in
  Magick.display (Obj.magic imglst4);
  Magick.write_image (Obj.magic imglst4) ~filename:"_lst.gif";
  Magick.destroy ();
;;

