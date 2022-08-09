<?php
// Check existence of id parameter before processing further
if(isset($_GET["id"]) && !empty(trim($_GET["id"]))){
    // Include config file
    require_once "config.php";
    $id = trim($_GET["id"]);
    
    $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 1";
    if($stmt = mysqli_prepare($link, $sql)){
        if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                    $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                    $foto1 = $row["foto"];
            } 
        }
    }
        
    $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 2";
    if($stmt = mysqli_prepare($link, $sql)){
        if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                $foto2 = $row["foto"];
            } 
        }
    }

    $sql = "SELECT * FROM imagenes WHERE id_producto = $id AND orden = 3";
    if($stmt = mysqli_prepare($link, $sql)){
        if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
            if(mysqli_num_rows($result) == 1){
                $row = mysqli_fetch_array($result,  MYSQLI_ASSOC);
                $foto3 = $row["foto"];
            } 
        }
    }

    mysqli_stmt_close($stmt);

    // Prepare a select statement
    $sql = "SELECT * FROM productos WHERE id_producto = ?";
    if($stmt = mysqli_prepare($link, $sql)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt, "i", $param_id);
        
        // Set parameters
        $param_id = trim($_GET["id"]);
        
        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt)){
            $result = mysqli_stmt_get_result($stmt);
    
            if(mysqli_num_rows($result) == 1){
                /* Fetch result row as an associative array. Since the result set contains only one row, we don't need to use while loop */
                $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
                
                // Retrieve individual field value
		$id = $row["id_producto"];
                $titulo = $row["titulo"];
                $descripcion = $row["descripcion"];
                $caracteristicas = $row["caracteristicas"];
		$existencia = $row["existencia"];
		$precio = $row["precio"];
            } else{
                // URL doesn't contain valid id parameter. Redirect to error page
                header("location: productos.php");
                exit();
            }
            
        } else{
            echo "Oops! Something went wrong. Please try again later.";
        }
    }
     
    // Close statement
    mysqli_stmt_close($stmt);
    
    // Close connection
    mysqli_close($link);
} else{
    // URL doesn't contain id parameter. Redirect to error page
    header("location: productos.php");
    exit();
}

if(isset($_GET["id_cliente"]) && !empty(trim($_GET["id_cliente"]))){
    $id_cliente =trim($_GET["id_cliente"]);
}
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $id_cliente = $_POST["id_c"];
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>VER</title>
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
                        <h1>Datos del Registro</h1>
                    </div>
		    <div class="form-group">
                        <label>N° Identificador</label>
                        <p class="form-control-static"><?php echo $row["id_producto"]; ?></p>
                    </div>
                    <div class="form-group">
                        <label>Titulo</label>
                        <p class="form-control-static"><?php echo $row["titulo"]; ?></p>
                    </div>
                    <div class="form-group">
                        <label>Descripcion</label>
                        <p class="form-control-static"><?php echo $row["descripcion"]; ?></p>
                    </div>
                    <div class="form-group">
                        <label>Caracteristicas</label>
                        <p class="form-control-static"><?php echo $row["caracteristicas"]; ?></p>
                    </div>
		    <div class="form-group">
                        <label>Existencia</label>
                        <p class="form-control-static"><?php echo $row["existencia"]; ?></p>
                    </div>
		    <div class="form-group">
                        <label>Precio en bitcoins</label>
                        <p class="form-control-static"><?php echo number_format( $row['precio']*0.0000026,6); ?></p>
                    </div>

                    <div class="form-group">
                        <label>Imagen 1</label>
                        <br>
                        <?php  
                        echo "<img height ='250 px' src = 'data:image/jpg;base64,".base64_encode($foto1)."'>";
                        ?>
                    </div>

                    <div class="form-group">
                        <label>Imagen 2</label><br>
                        <?php  
                        echo "<img height ='250 px' src = 'data:image/jpg;base64,".base64_encode($foto2)."'>";
                        ?>
                    </div>

                    <div class="form-group ">
                        <label>Imagen 3</label><br>
                        <?php  
                        echo "<img height ='250 px' src = 'data:image/jpg;base64,".base64_encode($foto3)."'>";
                        ?>
                    </div><br>


                    <input type="hidden" name="id_c" value="<?php echo $id_cliente; ?>"/>
                    <?php  
                        echo "<a href='productos.php?id_cliente=". $id_cliente ."' class='btn btn-primary'>Salir</a>"
                    ?>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>

