<?php
// Include config file
require_once "config.php";
 
// Define variables and initialize with empty values
//$name = $address = $salary = "";

//$name_err = $address_err = $salary_err = "";

$precio = $existencia = $id = "";
$titulo = $descripcion = $caracteristicas = "";

$precio_err = $existencia_err = $id_err = "";
$titulo_err = $descripcion_err = $caracteristicas_err = "";

$img1 = $img2 = $img3 = "";
$img1_err = $img2_err = $img3_err = "";

if(isset($_GET["id_cat"]) && !empty(trim($_GET["id_cat"]))){
    $id_cat =trim($_GET["id_cat"]);
}


// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cat = $_POST["id_subcat"];
    $completo = 0;

    // Validate id
    $input_id = trim($_POST["id"]);
    if(empty($input_id)){
        $id_err = "Por favor ingresa el numero de identificador.";
    } elseif(!ctype_digit($input_id)){
        $id_err = "Ingresa un numero identificador valido.";
    } else{
        $id = $input_id;
    }

    // Validate titulo
    $input_titulo = trim($_POST["titulo"]);
    if(empty($input_titulo)){
        $titulo_err = "Por favor ingresa el titulo del producto.";
    } else{
        $titulo = $input_titulo;
    }

     // Validate descripcion
    $input_descripcion = trim($_POST["descripcion"]);
    if(empty($input_descripcion)){
        $descripcion_err = "Por favor ingresa la descripcion del producto.";
    } else{
        $descripcion = $input_descripcion;
    }

      // Validate caracteristicas
    $input_caracteristicas = trim($_POST["caracteristicas"]);
    if(empty($input_caracteristicas)){
        $caracteristicas_err = "Por favor ingresa las caracteristicas del producto.";
    } else{
        $caracteristicas = $input_caracteristicas;
    }

    // Validate existencia
    $input_existencia = trim($_POST["existencia"]);
    if(empty($input_existencia)){
        $existencia_err = "Por favor ingresa la existencia del producto.";
    } elseif(!ctype_digit($input_existencia)){
        $existencia_err = "Por favor ingresa un número positivo.";
    } else{
        $existencia = $input_existencia;
    }

     // Validate precio
    $input_precio = trim($_POST["precio"]);
    if(empty($input_precio)){
        $precio_err = "Por favor ingresa el precio del producto.";     
    } elseif($input_precio < 0){			//elseif(!ctype_digit($input_precio)){
        $precio_err = "Por favor ingresa un número positivo.";
    } else{
        $precio = $input_precio;
    }

    //validando imagenes
    $input_img1 = trim($_FILES['archivo1']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img1) ){
        $img1_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img1 = $input_img1;
        echo $img1;

        //la imagen
        $foto1 = file_get_contents($_FILES['archivo1']['tmp_name']);


        //$temp = $_FILES['archivo1']['tmp_name'];

//        $directorio = $_SERVER['DOCUMENT_ROOT'].'/imagenes/';
        //$directorio = "__DIR__/var/www/html/imagenes/";
        //echo $directorio;

        //Para mover el archivo
        //move_uploaded_file($img1,"http://192.168.0.5/imagenes/".$img1);
        //if(move_uploaded_file($_FILES['archivo1']['tmp_name'],$directorio.$img1)){
        //    echo "Si se pudo";
        //}else{
           // echo "No se pude";
        //}
        //chmod('home/fer10/'.$img1, 0777);
    }

    $input_img2 = trim($_FILES['archivo2']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img2) ){
        $img2_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img2 = $input_img2;
        
        //la imagen
        $foto2 = file_get_contents($_FILES['archivo2']['tmp_name']);
    }

    $input_img3 = trim($_FILES['archivo3']['name']);
    //$input_img1 = trim($_POST["archivo1"]);
    if( empty($input_img3) ){
        $img3_err = "Ingresa la imagen";
    }else{
        //nombre de la imagen
        $img3 = $input_img3;
        
        //la imagen
        $foto3 = file_get_contents($_FILES['archivo3']['tmp_name']);
    }
    // Check input errors before inserting in database
    if(empty($id_err) && empty($titulo_err) && empty($descripcion_err) && empty($caracteristicas_err)&& empty($existencia_err) && empty($precio_err) && empty($img1_err) && empty($img2_err) && empty($img3_err)){
        // Prepare an insert statement

        $sql = "INSERT INTO productos VALUES(?, ?, ?, ?, ?, ?)";

	   if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "isssid", $param_id, $param_titulo, $param_descripcion, $param_caracteristicas, $param_existencia, $param_precio);
            // Set parameters
            $param_id = $id;
            $param_titulo = $titulo;
            $param_descripcion = $descripcion;
            $param_caracteristicas = $caracteristicas;
            $param_existencia = $existencia;
            $param_precio = $precio;

            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
                $completo = 1;
            } else{
                echo "Something went wrong. Please try again later.";
          }

        }
        // Close statement
        mysqli_stmt_close($stmt);

    //si todos los datos estan completos, insertalo en la tabla cat_productos
    if($completo == 1){
        $sql = "INSERT INTO imagenes(id_producto,imagen,orden ,foto) VALUES(?, ?, 1, ?)";
        if($stmt = mysqli_prepare($link, $sql)){
            mysqli_stmt_bind_param($stmt, "iss",$param_id_producto, $param_imagen, $param_foto1);
            // Set parameters
            $param_id_producto = $id;
            $param_imagen = $img1;
            $param_foto1 = $foto1;
            // Attempt to execute the prepared statement
            mysqli_stmt_execute($stmt);

        }
        mysqli_stmt_close($stmt);

        $sql = "INSERT INTO imagenes(id_producto,imagen,orden ,foto) VALUES(?, ?, 2, ?)";
        if($stmt = mysqli_prepare($link, $sql)){
            mysqli_stmt_bind_param($stmt, "iss",$param_id_producto, $param_imagen, $param_foto2);
            // Set parameters
            $param_id_producto = $id;
            $param_imagen = $img2;
            $param_foto2 = $foto2;
            // Attempt to execute the prepared statement
            mysqli_stmt_execute($stmt);

        }
        mysqli_stmt_close($stmt);

        $sql = "INSERT INTO imagenes(id_producto,imagen,orden ,foto) VALUES(?, ?, 3, ?)";
        if($stmt = mysqli_prepare($link, $sql)){
            mysqli_stmt_bind_param($stmt, "iss",$param_id_producto, $param_imagen, $param_foto3);
            // Set parameters
            $param_id_producto = $id;
            $param_imagen = $img3;
            $param_foto3 = $foto3;
            // Attempt to execute the prepared statement
            mysqli_stmt_execute($stmt);

        }
        mysqli_stmt_close($stmt);

        $sql = "INSERT INTO cat_producto VALUES(?,?)";
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "ii",$param_cat, $param_id);
            // Set parameters
            $param_cat = $id_cat;
            $param_id = $id;

            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records created successfully. Redirect to landing page
                header("location: productos.php");
                exit();
            } else{
                    echo "Something went wrong. Please try again later.";
            }

        }
         
            // Close statement
            mysqli_stmt_close($stmt);

    }
    
        // Close connection
        mysqli_close($link);
    }
}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Inserción</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h2>Inserción de un nuevo registro en la tabla productos</h2>
                    </div>
                    <p>Llena todos los campos y da clic en Aceptar para agregar el producto.</p>
                    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post" enctype="multipart/form-data">
                        <div class="form-group <?php echo (!empty($id_err)) ? 'has-error' : ''; ?>">
                            <label>Identificador del Producto</label>
                            <input type="text" name="id" class="form-control" value="<?php echo $id; ?>">
                            <span class="help-block"><?php echo $id_err;?></span>
                        </div>

			<div class="form-group <?php echo (!empty($titulo_err)) ? 'has-error' : ''; ?>">
                            <label>Titulo</label>
                            <input type="text" name="titulo" class="form-control" value="<?php echo $titulo; ?>">
                            <span class="help-block"><?php echo $titulo_err;?></span>
                        </div>


                        <div class="form-group <?php echo (!empty($descripcion_err)) ? 'has-error' : ''; ?>">
                            <label>Descripción</label>
                            <textarea name="descripcion" class="form-control"><?php echo $descripcion; ?></textarea>
                            <span class="help-block"><?php echo $descripcion_err;?></span>
                        </div>

			<div class="form-group <?php echo (!empty($caracteristicas_err)) ? 'has-error' : ''; ?>">
                            <label>Caracteristicas</label>
                            <textarea name="caracteristicas" class="form-control"><?php echo $caracteristicas; ?></textarea>
                            <span class="help-block"><?php echo $caracteristicas_err;?></span>
                        </div>



                        <div class="form-group <?php echo (!empty($existencia_err)) ? 'has-error' : ''; ?>">
                            <label>Existencia</label>
                            <input type="text" name="existencia" class="form-control" value="<?php echo $existencia; ?>">
                            <span class="help-block"><?php echo $existencia_err;?></span>
                        </div>

		                <div class="form-group <?php echo (!empty($precio_err)) ? 'has-error' : ''; ?>">
                            <label>Precio en Pesos Mexicanos</label>
                            <input type="text" name="precio" class="form-control" value="<?php echo $precio; ?>">
                            <span class="help-block"><?php echo $precio_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($img1_err )) ? 'has-error' : ''; ?>">
                            <label>Imagen 1</label>
                            <input type="file" name="archivo1" accept="image/png, .jpeg, .jpg">
                            <span class="help-block"><?php echo $img1_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($img2_err )) ? 'has-error' : ''; ?>">
                            <label>Imagen 2</label>
                            <input type="file" name="archivo2" accept="image/png, .jpeg, .jpg">
                            <span class="help-block"><?php echo $img2_err;?></span>
                        </div>

                        <div class="form-group <?php echo (!empty($img3_err )) ? 'has-error' : ''; ?>">
                            <label>Imagen 3</label>
                            <input type="file" name="archivo3" accept="image/png, .jpeg, .jpg">
                            <span class="help-block"><?php echo $img3_err;?></span>
                        </div>
                        
                        
                        

                        <input type="hidden" name="id_subcat" value="<?php echo $id_cat; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Aceptar">
                        <a href="productos.php" class="btn btn-default">Cancelar</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

