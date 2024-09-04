$(document).ready(function() {
    $('table.datatable').DataTable({
        autoWidth: true,
        paging: false,
        searching: false,
    });
});

$(window).on('resize', function() {
    $('table.datatable').DataTable().columns.adjust().draw();
});
