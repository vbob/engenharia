<%-- 
    Document   : adicionarUsuario
    Created on : 27/11/2017, 21:42:54
    Author     : vbob
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <title>Tela de Login</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <form method="post" action="adicionar.jsp">
            <table border="0" align="center">
                <h1>Adicionar Usuário</h1>
                <tr>
                    <td align="right">Nome:</td>
                    <td align="left"><input type="text" name="nome"></td>
                </tr>
                <tr>
                    <td align="right">Login:</td>
                    <td align="left"><input type="text" name="login"></td>
                </tr>
                <tr>
                    <td align="right">Senha</td>
                    <td align="left"><input type="password" name="senha"></td>
                </tr>
                <tr>
                    <td colspan="2" align="center"><input type="submit" value="Entrar"></td>
                </tr>
            </table>
        </form>
    </body>
</html>

